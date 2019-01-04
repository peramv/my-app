#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfconmgr_err_vmconnection_waitevent_failed : public CConditionObject
	{
	public:
		CBase_Ifds_bfconmgr_err_vmconnection_waitevent_failed() { }
		~CBase_Ifds_bfconmgr_err_vmconnection_waitevent_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VMCONNECTION_WAITEVENT_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured waiting for signal from VM connection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierter Adressenstandard nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error occured waiting for signal from VM connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de l'attente d'un signal de la connexion privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Error occured waiting for signal from VM connection.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



