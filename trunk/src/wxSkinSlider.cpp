/////////////////////////////////////////////////////////////////////////////////////////
// Name:		wxSkin
// Author:      René Kraus aka upCASE <himself@upcase.de>
// Copyright:   René Kraus (c)
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
//				with the addendum that you notify the author about projects using wxSkin
/////////////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUG__
	#pragma implementation "wxSkinSlider.h"
#endif

#include "wxSkinSlider.h"
#include "wxSkinEngine.h"


BEGIN_EVENT_TABLE(wxSkinSlider,wxSkinWindow)
	EVT_ENTER_WINDOW(wxSkinSlider::OnEnterWindowDummy)
	EVT_LEAVE_WINDOW(wxSkinSlider::OnLeaveWindow)
	EVT_MOTION(wxSkinSlider::OnMouseMotion)
	EVT_LEFT_UP(wxSkinSlider::OnLeftUp)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(wxSkinSlider,wxSkinWindow)
 
wxSkinSlider::wxSkinSlider()
	: wxSkinWindow()
{
	m_currentvalue = 0;
	m_maxvalue = 0;
}

wxSkinSlider::wxSkinSlider(wxWindow* parent,
 				int id,
 				bool type,
 				int max,
   				const wxPoint& pos,
         		const wxSize& size,
           		long style,
				const wxString& name)
	:wxSkinWindow(parent,id,pos,size,style,name,TYPE_SLIDER), m_maxvalue(max), m_isvertical(type)
{
	m_currentvalue = 0;

	m_bOver = false;
}

wxSkinSlider::~wxSkinSlider()
{
}
wxSize wxSkinSlider::DoGetBestSize() const
{
	if(bmp_normal.ISOK())
		return wxSize(bmp_normal.GetWidth(),bmp_normal.GetHeight());
	return wxSize(70,30);
}

void wxSkinSlider::DrawCustom(wxDC& dc)
{
	if(bmp_state2.ISOK() && bmp_extra.ISOK())
	{
	    wxImage bmp_fill(bmp_extra);
		//if(bmp_state2.Ok())
		//{
			m_sliderRect.width = bmp_state2.GetWidth();
			m_sliderRect.height = bmp_state2.GetHeight();
		//}

		int w, h;
		GetClientSize(&w,&h);
		
		int scale;
		if (m_isvertical)
		{
		    scale = (int)(((float)h/(float)m_maxvalue)*m_currentvalue);
		    if(scale >= h)
			    scale = h-bmp_state2.GetHeight();
		    m_sliderRect.y = scale;

		    if(m_bOver)
			    dc.DrawBitmap( bmp_over, 0, scale, true);
		    else
			    dc.DrawBitmap( bmp_state2, 0, scale, true);
	        dc.DrawBitmap(bmp_fill.Resize(wxSize(bmp_extra.GetWidth(), scale), wxPoint(0, 0)), 0, 0, true);
		}
		else
		{
		    scale = (int)(((float)w/(float)m_maxvalue)*m_currentvalue);
		    if(scale >= w)
			    scale = w-bmp_state2.GetWidth();
		    m_sliderRect.x = scale;

		    if(m_bOver)
			    dc.DrawBitmap( bmp_over, scale , 0, true);
		    else
			    dc.DrawBitmap( bmp_state2, scale , 0, true);
	        dc.DrawBitmap(bmp_fill.Resize(wxSize(scale, bmp_extra.GetHeight()), wxPoint(0, 0)), 0, 0, true);
		}
	}

}
int wxSkinSlider::GetRange() const
{
	return m_maxvalue;
}
int wxSkinSlider::GetValue() const
{
	return m_currentvalue;
}
void wxSkinSlider::SetRange(int range)
{
	m_maxvalue = range;
}

void wxSkinSlider::SetValue(int value)
{
	if(!HasCapture())
	{	m_currentvalue = value;
		Refresh();
	}
}

bool wxSkinSlider::GetType() const
{
    return m_isvertical;
}

void wxSkinSlider::SetType(bool type)
{
    m_isvertical = type;
}

void wxSkinSlider::OnMouseMotion(wxMouseEvent& event)
{
	wxPoint pt = event.GetPosition();

	if( HasCapture() && event.Dragging())
	{
		m_bOver = true;

		int w,h;
		GetClientSize(&w,&h);
		
		int scale;
		if (m_isvertical)
		{
		    scale = (int)(((float)m_maxvalue/(float)h)*pt.y);
		}
		else
		{
		    scale = (int)(((float)m_maxvalue/(float)w)*pt.x);
		}
		
		if(scale > m_maxvalue)
			scale = m_maxvalue;
		if(scale < 0)
			scale = 0;

		m_currentvalue = scale;

		wxCommandEvent evt(wxEVT_COMMAND_SLIDER_UPDATED,GetId());
		evt.SetInt(m_currentvalue);
		evt.SetEventObject(this);
		GetEventHandler()->ProcessEvent(evt);
	}
#if wxCHECK_VERSION(2, 7, 0)
	else if(m_sliderRect.Contains(pt))
#else
	else if(m_sliderRect.Inside(pt))
#endif
	{	m_bOver = true;
		CaptureMouse();
	}
	else
	{	m_bOver = false;
		if(HasCapture())
			ReleaseMouse();
	}

	Refresh();
}

void wxSkinSlider::OnLeftUp(wxMouseEvent& evt)
{
    if (HasCapture())
    {
        ReleaseMouse();
    }
}
