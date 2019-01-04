﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfbase_err_field_required_gui : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfbase_err_field_required_gui() { }
		~CBase_Infrastructure_bfbase_err_field_required_gui() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_REQUIRED_GUI")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field %FIELD% has not been validated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field '^' has not been validated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Feld %FIELD% wurde nicht gültig gesetzt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha validado el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% n'a pas été validé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld %FIELD% is niet gevalideerd")); }

        // Actions
	};
}



