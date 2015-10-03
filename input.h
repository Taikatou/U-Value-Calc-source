#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"
#include "s3ePointer.h"
#include "s3eKeyboard.h"
#include "s3eOSReadString.h"

#define MAX_TOUCHES     10

/**
 * @class Input
 *
 * @brief Input - The Input class is responsible for handling all pointer input.
 *
 * Example usage:
 * @code
 *    // Set up input systems
 *    g_pInput = new Input();
 *
 *    // Update
 *    while (!s3eDeviceCheckQuitRequest())
 *    {
 *        // Update input system
 *        g_pInput->Update();
 *    }
 *
 *    // Cleanup
 *    delete g_pInput;
 * @endcode
 *
 */
class Input
{
public:
    int             m_X, m_Y;           // Touched position
    bool            m_Touched;          // Touched status
    bool            m_PrevTouched;      // Previous touched status

public:
    Input();

    /**
     * @fn    void Input::Update()
     *
     * @brief Updates the input system, called every frame
     */
    void            Update();
    /**
     * @fn    void Input::Reset()
     *
     * @brief Resets touch status, usually called after a touch event has been acknowledged
     */
    void            Reset();

    // Callbacks
    static void     TouchButtonCB(s3ePointerEvent* event);
    static void     TouchMotionCB(s3ePointerMotionEvent* event);
    static void     MultiTouchButtonCB(s3ePointerTouchEvent* event);
    static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);

	bool		isPointerAvailable() const { return PointerAvailable; }	// Returns availability of the pointer
	bool		isKeysAvailable() const { return KeysAvailable; }		// Returns availability of keys
	bool		isOSKeyboardAvailable() const { return OSKeyboardAvailable; }	// Returns availability of on screen keyboard
	bool		isMultiTouch() const { return IsMultiTouch; }		// Returns multitouch capability
	int			getTouchCount() const;								// Get number of touches this frame
	bool		isKeyDown(s3eKey key) const;
	bool		isKeyUp(s3eKey key) const;
	bool		wasKeyPressed(s3eKey key) const;
	bool		wasKeyReleased(s3eKey key) const;
	const char* showOnScreenKeyboard(const char* prompt, int flags = 0, const char* default_text = NULL);

private:
	bool		PointerAvailable;				// true if a pointer is present
	bool		KeysAvailable;					// true if a key input is present
	bool		OSKeyboardAvailable;			// trie if on screen keyboard is available
	bool		IsMultiTouch;
};

extern Input* g_pInput;


#endif  // _INPUT_H
