#include "Image.h"


//Logging
#include "Core/Log.h"

namespace ProtOS {
    ScreenImage::ScreenImage(nlohmann::basic_json<>& config)
                    : m_Config(config) {
    	PROTOS_LOG_TRACE("ProtOS", "Loaded image from path: {0}", m_Config["path"]);

        std::vector<Magick::Image> frames;

        try {
            readImages(&frames, m_Config["path"]);
        } catch (std::exception& e) {
            if (e.what()) PROTOS_LOG_ERROR("ProtOS", "Error while loading image: {1}", m_Config["path"], e.what());
            return;
        }

        if(frames.empty()) {
            PROTOS_LOG_ERROR("ProtOS", "No image loaded.");
            return;
        }

        // Put together the animation from single frames. GIFs can have nasty
        // disposal modes, but they are handled nicely by coalesceImages()
        if(frames.size() > 1) Magick::coalesceImages(&m_Images, frames.begin(), frames.end());
        else m_Images.push_back(frames[0]);

        m_bHasAlpha = HasAlpha(m_Images[0]);
    }

    ScreenImage::~ScreenImage() {
        m_Images.clear();
    }

    void ScreenImage::OnUpdate(Timestep ts) {
        m_fLastFrameTime += ts.GetMilliseconds();
        int delay = m_Images[m_nFrame].animationDelay() * 10; // Convert to milliseconds.

        if(m_fLastFrameTime >= delay) {
            m_fLastFrameTime -= (float)delay;
            m_nFrame++;
        }

        if(m_nFrame >= m_Images.size()) m_nFrame = 0;
    }

    void ScreenImage::OnDraw(rgb_matrix::FrameCanvas* canvas) {
        for(int y = 0; y < m_Images[m_nFrame].rows(); y++) {
            for(int x = 0; x < m_Images[m_nFrame].columns(); x++) {
                const Magick::Color &c = m_Images[m_nFrame].pixelColor(x, y);

                if(!m_bHasAlpha || c.alphaQuantum() < MaxRGB) {
                    canvas->SetPixel((int) (m_Config["position"]["x"]) + x, (int) (m_Config["position"]["y"]) + y,
                                     ScaleQuantumToChar(c.redQuantum()),
                                     ScaleQuantumToChar(c.greenQuantum()),
                                     ScaleQuantumToChar(c.blueQuantum()));

                    if (m_Config["mirrored"]) {
                        canvas->SetPixel((int) (m_Config["position"]["x"]) +
                                         (m_Images[m_nFrame].columns() - ((x - (int) (m_Config["position"]["x"])))) +
                                         (canvas->width() - m_Images[m_nFrame].columns()),
                                         (int) (m_Config["position"]["y"]) + y,
                                         ScaleQuantumToChar(c.redQuantum()),
                                         ScaleQuantumToChar(c.greenQuantum()),
                                         ScaleQuantumToChar(c.blueQuantum()));
                    }
                }
            }
        }
    }

    bool ScreenImage::HasAlpha(const Magick::Image& image) {
        for(int y = 0; y < m_Images[m_nFrame].rows(); y++) {
            for (int x = 0; x < m_Images[m_nFrame].columns(); x++) {
                const Magick::Color &c = m_Images[m_nFrame].pixelColor(x, y);
                if(c.alphaQuantum() < MaxRGB) {
                    return true;
                }
            }
        }
        return false;
    }
}
