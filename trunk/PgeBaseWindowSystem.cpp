
/*! $Id$
 *  @file   PgeBaseWindowSystem.cpp
 *  @author Chad M. Draper
 *  @date   May 1, 2008
 *
 */

#include "version.h"
#include "PgeBaseWindowSystem.h"
#include "PgeException.h"

#include <windows.h>

namespace PGE
{
    //Constructor---------------------------------------------------------------
    BaseWindowSystem::BaseWindowSystem()
        : mWidth( 800 ),
          mHeight( 600 ),
          mTitle( "" ),
          mIsMinimized( false ),
          mIsPaused( false )
    {
    }

    //Destructor----------------------------------------------------------------
    BaseWindowSystem::~BaseWindowSystem()
    {
//        SDL_Quit();
    }

    //SetSize-------------------------------------------------------------------
    void BaseWindowSystem::SetSize( const unsigned long& w, const unsigned long& h )
    {
        mWidth  = w;
        mHeight = h;

        CreateSurface();
    }

//    // CreateSurface------------------------------------------------------------
//    void BaseWindowSystem::CreateSurface()
//    {
//        mSurface = SDL_SetVideoMode( mWidth, mHeight, 0, SDL_SWSURFACE );
//    }

//    //Init----------------------------------------------------------------------
//    void BaseWindowSystem::Init()
//    {
//        // Register SDL_Quit to be called at exit
//        atexit( SDL_Quit );
//
//        // Initialize the video
//        if ( SDL_Init( SDL_INIT_VIDEO ) )
//        {
//            std::string msg = std::string( "Unable to initialize SDL: " ) + SDL_GetError();
//            throw Exception( msg );
//        }
//
//        // Create a window with the specified height and width:
//        SetSize( mWidth, mHeight );
//        if ( !mSurface )
//        {
//            std::string msg = std::string( "Unable to setup video: " ) + SDL_GetError();
//            throw Exception( msg );
//        }
//
//        // Perform any additional initialization required by the sub-classed engine
//        AdditionalInit();
//    }

    //Init----------------------------------------------------------------------
    void BaseWindowSystem::Init()
    {
        AdditionalInit();
        mGameManager.Init();
    }

    //Run-----------------------------------------------------------------------
    void BaseWindowSystem::Run()
    {
        // Get the start time:
        //mLastTick   = Timer::GetTicks();
        mQuit       = false;

        while ( !mQuit )
        {
            // Handle user input
            HandleInput();

            if ( mIsMinimized )
            {
                // If the window is minimized, the game is paused.
                WaitMessage();
            }
            else
            {
                // Update the logic:
                //DoLogic();
                mGameManager.PrepareFrame();

                // Lock the surface before rendering:
                LockSurface();

                // Update the display:
                //DoRender();
                mGameManager.RenderFrame();

                // Unlock the surface before rendering:
                UnlockSurface();
            }
        }

        // Cleanup and terminate:
        Shutdown();
    }

//    //HandleInput---------------------------------------------------------------
//    void BaseWindowSystem::HandleInput()
//    {
//        SDL_Event event;
//        while ( SDL_PollEvent( &event ) )
//        {
//            switch ( event.type )
//            {
//            case SDL_KEYDOWN:
//                {
//                    // If the escape key was pressed, terminate the application.
//                    // All other key processing gets passed to the derived class.
//                    if ( event.key.keysym.sym == SDLK_ESCAPE )
//                    {
//                        mQuit = true;
//                        break;
//                    }
//
//                    KeyDown( event.key.keysym.sym );
//                }
//                break;
//
//            case SDL_KEYUP:
//                KeyUp( event.key.keysym.sym );
//                break;
//
//            case SDL_QUIT:
//                mQuit = true;
//                break;
//
//            case SDL_MOUSEMOTION:
//                MouseMove( event.button.button,
//                            event.motion.x,
//                            event.motion.y,
//                            event.motion.xrel,
//                            event.motion.yrel );
//                break;
//
//            case SDL_MOUSEBUTTONUP:
//                MouseButtonUp( event.button.button,
//                            event.motion.x,
//                            event.motion.y,
//                            event.motion.xrel,
//                            event.motion.yrel );
//                break;
//
//            case SDL_MOUSEBUTTONDOWN:
//                MouseButtonDown( event.button.button,
//                            event.motion.x,
//                            event.motion.y,
//                            event.motion.xrel,
//                            event.motion.yrel );
//                break;
//
//            case SDL_ACTIVEEVENT:
//                if ( event.active.state & SDL_APPACTIVE )
//                {
//                    if ( event.active.gain )
//                    {
//                        mIsMinimized = false;
//                        MakeActive();
//                    }
//                    else
//                    {
//                        mIsMinimized = true;
//                        MakeInactive();
//                    }
//                }
//                break;
//            }
//        }
//    }

//    //DoLogic-------------------------------------------------------------------
//    void BaseWindowSystem::DoLogic()
//    {
//        // Get the elapsed time:
//        unsigned long curTick = Timer::GetTicks();
//        unsigned long elapsedTicks = curTick - mLastTick;
//        mLastTick = curTick;
//
//        UpdateLogic( mTimer.GetElapsedTime() );
//
//        // Update the tick counter:
//        mTickCounter += elapsedTicks;
//    }
//
//    //DoRender------------------------------------------------------------------
//    void BaseWindowSystem::DoRender()
//    {
//        // Update the frame counter:
//        ++mFrameCounter;
//
//        if ( mTickCounter > 1000 )
//        {
//            mCurrentFPS = mFrameCounter;
//            mFrameCounter = 0;
//            mTickCounter = 0;
//        }
//
//        // Lock the surface:
//        LockSurface();
//
//        // Render the scene:
//        Render(  );
//
//        // Unlock the surface:
//        UnlockSurface();
//    }

    //SetTitle------------------------------------------------------------------
    void BaseWindowSystem::SetTitle( const String& title )
    {
        mTitle = title;
        //SDL_WM_SetCaption( mTitle.c_str(), 0 );
    }

    //GetTitle------------------------------------------------------------------
    const String& BaseWindowSystem::GetTitle() const
    {
        return mTitle;
    }

    //GetSurface----------------------------------------------------------------
//    SDL_Surface* BaseWindowSystem::GetSurface() const
//    {
//        return mSurface;
//    }

    //GetFPS--------------------------------------------------------------------
    unsigned long BaseWindowSystem::GetFPS() const
    {
        return 0;
        //return mCurrentFPS;
    }

    //GetVersion----------------------------------------------------------------
    std::string BaseWindowSystem::GetVersion() const
    {
        std::string version = AutoVersion::FULLVERSION_STRING;

        return version;
    }

} // namespace PGE
