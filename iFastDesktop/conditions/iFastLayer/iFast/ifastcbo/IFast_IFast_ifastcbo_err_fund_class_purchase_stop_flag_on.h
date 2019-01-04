#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_purchase_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_purchase_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_fund_class_purchase_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUND% and %CLASS% has Purchase stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fonds und Klasse : Für Fonds %FUND% und Klasse %CLASS% ist das Kaufstopp--Kennzeichen  aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondo y clase no válidos: %FUND% y %CLASS% tiene el flag de detención de compra activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt d'achat du fonds %FUND% et de la classe %CLASS% est activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige fonds en categorie: voor %FUND% en %CLASS% is de vlag voor het stoppen van de aankoop aangezet")); }

        // Actions
	};
}



