#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_group_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_group_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_group_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GROUP_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account belongs to shareholder group %GROUP_CODE%. %TRADE_TYPE% stop flag has been set to Yes.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le compte appartient au groupe d'actionnaires %GROUP_CODE%. L'indicateur d'arret %TRADE_TYPE% a ete defini sur Oui.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto gehört zur Aktionärsgruppe %GROUP_CODE%. %TRADE_TYPE%Stop-Kennzeichen wurde auf Ja gesetzt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta pertenece al grupo de accionistas %GROUP_CODE%. %TRADE_TYPE% El flag de detención se ha definido en Sí.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte appartient au groupe d'actionnaires %GROUP_CODE%. Le signal d'arrêt %TRADE_TYPE% a été activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account behoort bij aandeelhoudersgroep %GROUP_CODE%. %TRADE_TYPE% eindvlag is ingesteld op Ja")); }

        // Actions
	};
}



