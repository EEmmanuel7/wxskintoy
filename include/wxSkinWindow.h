/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      René Kraus aka upCASE <himself@upcase.de>
// Copyright:   René Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef __WXSKINWINDOW_H
#define __WXSKINWINDOW_H

#include <wx/wx.h>
#include <wx/image.h>

enum{
	TYPE_BUTTON,
	TYPE_CHECKBOX,
	TYPE_RADIOBUTTON,
	TYPE_GAUGE,
	TYPE_SLIDER,
	TYPE_RADIOBUTTTON,
	TYPE_PANEL,

	TYPE_TEXT
};

///wxSkinWindow is the abstract base class for all skinned controls in wxSkin
/**wxSkinWindow manages the skin files for all controls in wxSkin. In addition to that it handles the most basic
events, like painting and sizing a control. Drawing the "over" state is also done here.
*/
class wxSkinWindow : public wxWindow
{
	bool m_bInside;
protected:
	wxImage bmp_normal;
	wxImage bmp_state2;
	wxImage bmp_over;
	wxImage bmp_disabled;
	wxImage bmp_extra;
	int m_type;
	bool m_bScaleFill;
public:
	///Contructor
	wxSkinWindow(){};
	///Standard Contructor
	wxSkinWindow(wxWindow* parent,
				wxWindowID id,
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize,
				long style = wxNO_BORDER,
				const wxString& name = wxPanelNameStr,
				const int type = -1);

	///Set the normal, meaning standard skin
	void SetNormalSkin(const wxImage& skin = wxNullImage);
	///Set the "second state" skin
	/**What this skin image actually contains is up to the control derived from wxSkinWindow.
	For a button for example this is the skin in "pressed" state.
	*/
	void SetState2Skin(const wxImage& skin = wxNullImage);
	///Set the skin displayed when the mouse is over the control.
	void SetOverSkin(const wxImage& skin = wxNullImage);
	///Set a skin for disabled state.
	void SetDisabledSkin(const wxImage& skin = wxNullImage);
	///Set extra skin(some controls that need more skin).
	void SetExtraSkin(const wxImage& skin = wxNullImage);

	bool SetShape(const wxRegion& region);
	bool SetShape(const wxImage& img);
	bool SetShape(const wxBitmap& img);

	///Sets "scaled" mode. In "scaled" mode the skin will be scaled to exactly mathc the controls size.
	void SetScaleFill(bool b){ m_bScaleFill = b;}

	int GetSkinWindowType(){ return m_type; }

	///Overwrite this method in derived classses
	/**This method will be called after the standard drawing action has been completed. This allows to do some non-standard
	drawing in dervied controls.
	*/
	virtual void DrawCustom(wxDC& dc) = 0;

	virtual bool HasTransparentBackground() const {return true;}
private:
	void OnErase(wxEraseEvent& e);
	void OnSize(wxSizeEvent& e);
	void OnPaint(wxPaintEvent& e);
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnLeaveWindow(wxMouseEvent& WXUNUSED(event));
	
	DECLARE_ABSTRACT_CLASS(wxSkinWindow);
	DECLARE_EVENT_TABLE()
};
#endif //__WXSKINWINDOW_H
