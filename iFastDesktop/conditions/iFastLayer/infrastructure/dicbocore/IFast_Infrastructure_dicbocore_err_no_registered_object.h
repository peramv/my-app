#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_no_registered_object : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_no_registered_object() { }
		~CIFast_Infrastructure_dicbocore_err_no_registered_object() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_REGISTERED_OBJECT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object %OBJECT% has not been registered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Object '^' has not been registered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt %OBJECT% wurde nicht registriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto %OBJECT% no se ha registrado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet %OBJECT% n'a pas été enregistré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object %OBJECT% is niet geregistreerd")); }

        // Actions
	};
}



