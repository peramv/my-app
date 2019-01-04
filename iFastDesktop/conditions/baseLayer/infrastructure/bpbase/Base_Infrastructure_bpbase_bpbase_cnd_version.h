#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bpbase_cnd_version : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bpbase_cnd_version() { }
		~CBase_Infrastructure_bpbase_bpbase_cnd_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BPBASE_CND_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pointer to object is not valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pointer to object is not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Zeiger zum Objekt ist nicht gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Puntero a objeto no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pointeur à objet invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pointer naar object is ongeldig")); }

        // Actions
	};
}



