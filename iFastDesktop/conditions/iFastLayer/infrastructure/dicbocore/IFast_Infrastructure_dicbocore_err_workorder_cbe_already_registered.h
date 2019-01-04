#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_workorder_cbe_already_registered : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_workorder_cbe_already_registered() { }
		~CIFast_Infrastructure_dicbocore_err_workorder_cbe_already_registered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WORKORDER_CBE_ALREADY_REGISTERED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Work Order CBE already registered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Work Order CBE already registered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE bereits registriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("CBE de orden de trabajo ya registrado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le CBE de l'ordre électronique a déjà été enregistré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Werkorder CBE is al geregistreerd")); }

        // Actions
	};
}



