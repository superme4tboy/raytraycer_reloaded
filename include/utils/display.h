#pragma once
#include <SFML/Graphics.hpp>

class Display
{
private:
    double m_aspect_ratio{};
    int m_window_height{};
    int m_window_width{};

public:

    Display(int window_width, int window_height)
    {
        m_window_width = window_width;
        m_window_height = window_height;
        m_aspect_ratio = (float) window_width / (float)window_height;
    }

    Display(int window_width, float aspect_ratio)
    {
        m_window_width = window_width;
        m_aspect_ratio = aspect_ratio;
        m_window_height = static_cast<int>(window_width / aspect_ratio);
    }

    void changeResolution(int window_width, int window_height)
    {
        m_window_width = window_width;
        m_window_height = window_height;
        m_aspect_ratio = window_width / window_height;
    }

    int getDisplayHeight() const
    {
        return m_window_height;
    }

    int getDisplayWidth() const
    {
        return m_window_width;
    }

    double getDisplayRatio() const
    {
        return m_aspect_ratio;
    }

    /**
     * @brief Get the Position in an Array where the first component of RGBA is located
     * 
     * @param x framebuffer x-Value start at the top left Corner
     * @param y framebuffer y-Value start at the top left Corner
     * @return int the position in the array where the first component is
     */
    int getFramebufferPos(int x, int y)
    {
        if (x < m_window_width + 1 && y < m_window_height + 1)
        {
            return (((y * m_window_width) + x) * 4);
        }
        else
        {
            throw std::invalid_argument("x or y is too big for the given window size!!");
        }
    }
};