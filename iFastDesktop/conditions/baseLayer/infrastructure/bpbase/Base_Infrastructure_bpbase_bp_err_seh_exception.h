#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_seh_exception : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_seh_exception() { }
		~CBase_Infrastructure_bpbase_bp_err_seh_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_SEH_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Work Order CBE Key duplicated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Work Order CBE Key duplicated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE-Schlüssel dupliziert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Clave CBE de orden de trabajo repetida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La clé CBE de l'ordre électronique a été copiée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Werkorder CBE-sleutel is gedupliceerd")); }

        // Actions
	};
}



