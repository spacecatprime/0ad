#include "precompiled.h"

#include "wx/sysopt.h"
#include "wx/wfstream.h"
#include "wx/filename.h"
#include "wx/image.h"

#include "ToolButton.h"
#include "ScenarioEditor/Tools/Common/Tools.h"
#include "ScenarioEditor/SectionLayout.h"
#include "General/Datafile.h"

BEGIN_EVENT_TABLE(ToolButton, wxButton)
	EVT_BUTTON(wxID_ANY, ToolButton::OnClick)
END_EVENT_TABLE()

ToolButton::ToolButton
	(ToolManager& toolManager, wxWindow *parent, const wxString& label, const wxString& toolName, const wxSize& size, long style)
	: wxButton(parent, wxID_ANY, label, wxDefaultPosition, size, style)
	, m_ToolManager(toolManager)
	, m_Tool(toolName)
{
	// Explicitly set appearance, so that the button is always owner-drawn
	// (by the wxButton code), rather than initially using the native
	// (fixed colour) button appearance.
	SetSelectedAppearance(false);

	RegisterToolButton(this, toolName);
}

void ToolButton::OnClick(wxCommandEvent& WXUNUSED(evt))
{
	// Toggle on/off
	if (m_Selected)
		m_ToolManager.SetCurrentTool(_T(""));
	else
		m_ToolManager.SetCurrentTool(m_Tool);
}

void ToolButton::SetSelectedAppearance(bool selected)
{
	m_Selected = selected;
	if (selected)
		SetBackgroundColour(wxColour(0xee, 0xcc, 0x55));
	else
		SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
}

//////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(ToolButtonBar, wxToolBar)
	EVT_TOOL(wxID_ANY, ToolButtonBar::OnTool)
END_EVENT_TABLE()

ToolButtonBar::ToolButtonBar(ToolManager& toolManager, wxWindow* parent, SectionLayout* sectionLayout, int baseID)
: wxToolBar(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTB_FLAT|wxTB_HORIZONTAL)
, m_ToolManager(toolManager), m_SectionLayout(sectionLayout), m_Id(baseID), m_Size(-1)
{
	/* "msw.remap: If 1 (the default), wxToolBar bitmap colours will be remapped
	   to the current theme's values. Set this to 0 to disable this functionality,
	   for example if you're using more than 16 colours in your tool bitmaps." */
	wxSystemOptions::SetOption(wxT("msw.remap"), 0); // (has global effect)
}

void ToolButtonBar::AddToolButton(const wxString& shortLabel, const wxString& longLabel,
								  const wxString& iconPNGFilename, const wxString& toolName,
								  const wxString& sectionPage)
{
	wxFileName iconPath (_T("tools/atlas/toolbar/"));
	iconPath.MakeAbsolute(Datafile::GetDataDirectory());
	iconPath.SetFullName(iconPNGFilename);
	wxFFileInputStream fstr (iconPath.GetFullPath());
	if (! fstr.Ok())
	{
		wxLogError(_("Failed to open toolbar icon file '%s'"), iconPath.GetFullPath().c_str());
		return;
	}
	wxImage img (fstr, wxBITMAP_TYPE_PNG);
	if (! img.Ok())
	{
		wxLogError(_("Failed to load toolbar icon image '%s'"), iconPath.GetFullPath().c_str());
		return;
	}
	
	if (m_Size == -1)
	{
		m_Size = img.GetWidth();
		SetToolBitmapSize(wxSize(m_Size, m_Size));
	}

	if (img.GetWidth() != m_Size || img.GetHeight() != m_Size)
		img = img.Scale(m_Size, m_Size);

	AddCheckTool(m_Id, shortLabel, wxBitmap(img), wxNullBitmap, longLabel);
	m_Buttons[m_Id] = Button(toolName, sectionPage);
	
	RegisterToolBarButton(this, m_Id, toolName);

	++m_Id;
}

void ToolButtonBar::OnTool(wxCommandEvent& evt)
{
	std::map<int, Button>::iterator it = m_Buttons.find(evt.GetId());
	wxCHECK_RET(it != m_Buttons.end(), _T("Invalid toolbar button"));
	m_ToolManager.SetCurrentTool(it->second.name);
	if (! it->second.sectionPage.IsEmpty())
		m_SectionLayout->SelectPage(it->second.sectionPage);
}
