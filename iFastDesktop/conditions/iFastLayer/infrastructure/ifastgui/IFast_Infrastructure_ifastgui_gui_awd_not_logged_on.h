#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_awd_not_logged_on : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_awd_not_logged_on() { }
		~CIFast_Infrastructure_ifastgui_gui_awd_not_logged_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_NOT_LOGGED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction backed out.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transaction backed out.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion nicht ausgeführt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se canceló la transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction annulée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De transactie is gestopt")); }

        // Actions
	};
}



