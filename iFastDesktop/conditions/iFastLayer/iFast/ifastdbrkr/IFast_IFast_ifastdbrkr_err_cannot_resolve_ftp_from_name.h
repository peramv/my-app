#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_resolve_ftp_from_name : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_resolve_ftp_from_name() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_resolve_ftp_from_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_RESOLVE_FTP_FROM_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to resolve FTP host by name.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FTP-Host kann nicht nach Name gelöst werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible resolver el host FTP por nombre.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de résoudre l'hôte RTS par nom.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("FTP-host kon niet op naam worden ontbonden")); }

        // Actions
	};
}



