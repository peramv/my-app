#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawd23_diawd23_awd_exception : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawd23_diawd23_awd_exception() { }
		~CIFast_Infrastructure_diawd23_diawd23_awd_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_AWD_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nAWD exception thrown.\n%AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nAWD exception thrown.\n%AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nAWD-Ausnahme ist aufgetreten.\n%AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nEl sistema devolvió una excepción de AWD.\n%AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\n Une exception AWD a été renvoyée. \n %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nAWD-exceptie opgetreden.\n%AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



