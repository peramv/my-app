﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_return_view_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_return_view_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_return_view_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RETURN_VIEW_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account may only have one Nominee Owner.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account may only have one Nominee Owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto hat eventuell nur einen Bevollmächtigten Inhaber")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta sólo puede tener un propietario nominatario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte ne peut avoir qu'un seul propriétaire nominé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account kan slechts één gevolmachtigde eigenaar hebben")); }

        // Actions
	};
}



