#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_no_work_session : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_no_work_session() { }
		~CIFast_Infrastructure_vision_err_no_work_session() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_WORK_SESSION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\n\nOLE exception thrown. \nMessage: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nOLE exception thrown. \nMessage: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nOLE-Ausnahme ist aufgetreten. \nMeldung: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n\nEl sistema devolvió una excepción OLE. \nMensaje: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Une exception OLE a été renvoyée. \n Message : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nOLE-exceptie opgetreden. \nBericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



