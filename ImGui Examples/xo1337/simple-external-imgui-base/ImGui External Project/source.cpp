#include "renderer.hpp"

int main( )
{
    m_renderer = new renderer( );

    m_renderer->on_style = [ ] ( ImGuiStyle* style )
    {
        // You can do your styling here :)
        style->Colors[ImGuiCol_WindowBg] = ImColor( 100 , 100 , 100 );
    };

    m_renderer->on_tick = [ ] ( ImDrawList* drawlist , ImGuiViewport* viewport , ImVec2 size )
    {
        // Here is where the main loop happens, this is where you'd call ImGui::Begin for your
        // things, etc. Everything is ready for you to use, such as the drawlist API, viewport, and size of your window :)

        if ( m_renderer->is_open( ) )
        {
            static bool open = true;
            if (open) {
                if (!ImGui::Begin("HamMafia.co", &open)) {
                    ImGui::End();
                }
                else {
                    ImGui::Text("RT %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::End();
                }
            }
        }
    };

    m_renderer->on_message = [ ] ( WPARAM key )
    {
        // This is your WNDPROC message handler
        // This event handler only accepts a key pressed.

        char pressed = static_cast<char>( key ); 
        printf( "Key %c was pressed.\n" , pressed );

        if ( key == VK_INSERT ) // IF INSERT PRESSED
        {
            // Set menu open state
            m_renderer->set_open( !m_renderer->is_open() );
        }
    };

    m_renderer->create( true );
    m_renderer->destroy( );

    delete m_renderer;
    return 0;
}