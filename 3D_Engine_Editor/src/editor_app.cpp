#include <editor_app.hpp>



editor_app::editor_app(uint16_t _width, uint16_t _height,
				       const std::string_view& _editor_name)
		: application(_width, _height, _editor_name)
{ }

/*
//-----------------------------------------------------------------------------------------------------------------//   
m_window_ptr->addEventListener<Events::Resize>(
    [this](const ResizeEventData& _size) -> void
    {
        LOG_INFO("[RESIZE EVENT] Window '{0}', size: {1}x{2}", m_window_ptr->getTitle(), _size.width, _size.height);
        render::open_gl::renderer::setViewport(_size.width, _size.height);
    });

m_window_ptr->addEventListener<Events::Close>(
    [this]() -> void
    {
        LOG_INFO("[CLOSE EVENT] Window '{0}' closed", m_window_ptr->getTitle());
        m_is_closed = true;
    });
//-----------------------------------------------------------------------------------------------------------------//
*/