#include "ScreenImage.h"

//Logging
#include "Core/Log.h"

using namespace cimg_library;

namespace ProtOS {
    ScreenImage::ScreenImage(const nlohmann::basic_json<>& config) {
	PROTOS_LOG_TRACE("ProtOS", "Loaded image from path: {0}", config["path"]);
        m_Image = new CImg<uint8_t>(std::string(config["path"]).c_str());
    }

    ScreenImage::~ScreenImage() {
        if(m_Image)
            delete m_Image;
    }

    void ScreenImage::OnUpdate(Timestep ts) {

    }

    void ScreenImage::OnDraw(rgb_matrix::FrameCanvas* canvas) {
	for(int x = 0; x < m_Image->width(); x++) {
		for(int y = 0; y < m_Image->height(); y++) {
			canvas->SetPixel(x, y, *m_Image->data(x, y, 0, 0),
					       *m_Image->data(x, y, 0, 1),
					       *m_Image->data(x, y, 0, 2));
		}
	}
	//SetImage(canvas, 0, 0, m_Image->begin(), m_Image->size(), m_Image->width(), m_Image->height(), true); 
    }
}
