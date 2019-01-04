#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_gui_gui_encorr_ole_error : public CConditionObject
	{
	public:
		CBase_Ifds_gui_gui_encorr_ole_error() { }
		~CBase_Ifds_gui_gui_encorr_ole_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ENCORR_OLE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("gui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto wurden Transfers/Börsenhandel gestoppt. Automatischer Transfer kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("OLE Automation Error:%OLEMSG%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'automatisation OLE : %OLEMSG%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("OLE-automatiseringsfout:%OLEMSG%")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



