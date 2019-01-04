#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_fund_class_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% and Class %CLASS% has %TRADE_TYPE% stop flag turned on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'indicateur pour arrêter les %TRADE_TYPE% est active pour le fonds %FUND% et catégorie %CLASS%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Fonds %FUND% und Klasse %CLASS% ist das Stopp-Kennzeichen aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo %FUND% y la clase %CLASS% tiene el flag de dentición %TRADE_TYPE% activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt %TRADE_TYPE% du fonds %FUND% et de la classe %CLASS% est activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor fonds %FUND% en categorie %CLASS% is de %TRADE_TYPE% eindvlag aangezet")); }

        // Actions
	};
}



