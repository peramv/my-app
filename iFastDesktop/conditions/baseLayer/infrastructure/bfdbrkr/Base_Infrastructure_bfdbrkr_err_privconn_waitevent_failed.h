#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_err_privconn_waitevent_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_err_privconn_waitevent_failed() { }
		~CBase_Infrastructure_bfdbrkr_err_privconn_waitevent_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_WAITEVENT_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt Dollar-Wiederanlage nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\n Une exception AWD a été renvoyée. \n %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%AWD_EXCEPTION_MESSAGE%\n\nAWD-exceptie opgetreden.\n%AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Dollar-Wiederanlage und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el monto de reinversión y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



