﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_group_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_group_code() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_group_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GROUP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Group Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Group Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Gruppencode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de grupo no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de groupe invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige groepscode")); }

        // Actions
	};
}



