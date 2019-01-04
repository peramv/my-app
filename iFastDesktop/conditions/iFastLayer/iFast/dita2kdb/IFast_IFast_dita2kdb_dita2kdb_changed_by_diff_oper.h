﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_changed_by_diff_oper : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_changed_by_diff_oper() { }
		~CIFast_IFast_dita2kdb_dita2kdb_changed_by_diff_oper() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_CHANGED_BY_DIFF_OPER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Profile has no access today.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Acces refuse au profil aujourd'hui")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Mit diesem Profil heute kein Zugriff")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - El perfil no tiene acceso hoy")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – impossible d'accéder au profil aujourd'hui.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Profiel heeft vandaag geen toegang")); }

        // Actions
	};
}



