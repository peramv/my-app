#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfconmgr_err_vmconnection_notify_failed : public CConditionObject
	{
	public:
		CBase_Ifds_bfconmgr_err_vmconnection_notify_failed() { }
		~CBase_Ifds_bfconmgr_err_vmconnection_notify_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VMCONNECTION_NOTIFY_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Notification error occured to VM private connection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Scheck nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Notification error occured to VM private connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une notification d'erreur s'est produite dans la connexion privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Notification error occured to VM private connection.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



