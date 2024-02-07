#include "CIMOBJRender.hpp"

#include <filesystem>

#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2)

VTK_MODULE_INIT(vtkInteractionStyle)

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOBJReader.h>
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include <vtkPNGReader.h>
#include <vtkProperty.h>

// 获取文件后缀
std::string getFileExtension(const std::string &filePath) {
    size_t lastDotPos = filePath.find_last_of('.');

    if (lastDotPos != std::string::npos) {
        return filePath.substr(lastDotPos + 1);
    }

    return "";
}


CIMOBJRender::CIMOBJRender(const std::string &CIMPath) {
    auto cimSynthetic = CreateCIMSynthetic();
    cimSynthetic->fromJson(CIMPath.c_str());

    std::filesystem::path pathObj(CIMPath);
    std::filesystem::path parentPath = pathObj.parent_path();

    for (int i = 0; i < cimSynthetic->getEntitiesCount(); i++) {
        auto entity = cimSynthetic->getEntityFromCode(cimSynthetic->getEntityCodeFromIndex(i));

        std::string objPath;
        std::string texturePath;

        for (int j = 0; j < entity->getComponentsCount(); j++) {
            auto component = cimSynthetic->getComponentFromCode(entity->getComponent(j)->getCode().c_str());

            if(component == nullptr)
                continue;

            // 是否是空间几何
            if (component->getComponentType() == Component::SPATIALGEOMETRY) {
                auto geo = (Component::SpatialGeometry *) component;

                // 是否是外联数据
                if (geo->getSpatialGeometryType() != Component::SpatialGeometryType::EXTERNALGEO)
                    continue;

                auto externalData = cimSynthetic->getExternalDataFromCode(geo->getGeometry().c_str());

                // 是否是OBJ文件
                if (externalData->getDataFormat() != NNU::OpenCIM::Common::OBJ)
                    continue;

                objPath = parentPath.string() + "//" + externalData->getOuterUrl();

                std::cout << objPath << std::endl;
            }

            // 是否是属性
            if (component->getComponentType() == Component::PROPERTY) {
                auto property = (Component::Property *) component;

                // 是否是漫反射纹理
                if (property->getFieldName() != MaterialType[9])
                    continue;

                auto externalData = cimSynthetic->getExternalDataFromCode(property->getFieldValue().c_str());

                texturePath = parentPath.string() + "//" + externalData->getOuterUrl();

                std::cout << texturePath << std::endl;
            }
        }

        _objs.emplace_back(objPath);
        _textures.emplace_back(texturePath);
    }

    std::cout << _objs.size() << std::endl;
}

void CIMOBJRender::render() {
    std::vector<vtkSmartPointer<vtkActor>> actors;

    // 2. 读取所有的Obj文件并可视化
    for (int i = 0; i < _objs.size(); i++) {
        auto objPath = _objs[i];
        auto texturePath = _textures[i];

        vtkSmartPointer<vtkOBJReader> obj_reader = vtkSmartPointer<vtkOBJReader>::New();
        obj_reader->SetFileName(objPath.c_str());
        obj_reader->Update();

        vtkSmartPointer<vtkTexture> texture;
        if (getFileExtension(texturePath) == "png") {
            vtkSmartPointer<vtkPNGReader> pngReader = vtkSmartPointer<vtkPNGReader>::New();
            pngReader->SetFileName(texturePath.c_str());
            pngReader->Update();
            texture = vtkSmartPointer<vtkTexture>::New();
            texture->SetInputConnection(pngReader->GetOutputPort());
        } else if (getFileExtension(texturePath) == "jpg") {
            vtkSmartPointer<vtkJPEGReader> jpegReader = vtkSmartPointer<vtkJPEGReader>::New();
            jpegReader->SetFileName(texturePath.c_str());
            jpegReader->Update();
            texture = vtkSmartPointer<vtkTexture>::New();
            texture->SetInputConnection(jpegReader->GetOutputPort());
        }

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(obj_reader->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->SetTexture(texture);

        actors.push_back(actor); // 添加actor到vector中
    }

    // 3. 创建渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1, 1, 1); // 设置背景颜色为白色

    vtkSmartPointer<vtkRenderWindow> render_window = vtkSmartPointer<vtkRenderWindow>::New();
    render_window->SetSize(800, 600);
    render_window->AddRenderer(renderer);

    // 4. 创建交互式渲染窗口
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(render_window);

    // 5. 添加所有的Actor到渲染器并执行渲染
    for (const auto &actor: actors) {
        renderer->AddActor(actor);
    }

    renderer->ResetCamera();
    render_window->Render();

    // 6. 开始交互
    interactor->Start();
}
