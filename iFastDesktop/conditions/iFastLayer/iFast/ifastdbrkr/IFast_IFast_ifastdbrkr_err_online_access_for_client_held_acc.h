#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_online_access_for_client_held_acc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_online_access_for_client_held_acc() { }
		~CIFast_IFast_ifastdbrkr_err_online_access_for_client_held_acc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLINE_ACCESS_FOR_CLIENT_HELD_ACC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("On-Line Access allowed only for client-held accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Online-Zugriff nur für kundengeführte Konten erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite el acceso en línea para cuentas de cliente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'accès en ligne n'est autorisé que pour les comptes détenus par des clients.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Online toegang is uitsluitend toegestaan voor accounts op naam van klant")); }

        // Actions
	};
}



