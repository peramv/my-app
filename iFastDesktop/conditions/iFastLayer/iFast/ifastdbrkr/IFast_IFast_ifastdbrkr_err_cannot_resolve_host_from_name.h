#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_resolve_host_from_name : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_resolve_host_from_name() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_resolve_host_from_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_RESOLVE_HOST_FROM_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to resolve RTS host by name.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verbindungsanfrage-Host kann nicht nach Namen gelöst werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible resolver el host RTS por nombre.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de résoudre l'hôte RTS par nom.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RTS-host kon niet op naam worden gevonden")); }

        // Actions
	};
}



