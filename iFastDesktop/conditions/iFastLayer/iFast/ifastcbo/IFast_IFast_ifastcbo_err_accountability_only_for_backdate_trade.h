#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_accountability_only_for_backdate_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_accountability_only_for_backdate_trade() { }
		~CIFast_IFast_ifastcbo_err_accountability_only_for_backdate_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNTABILITY_ONLY_FOR_BACKDATE_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountability code only applicable to backdated trade.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Code de responsabilite applicable uniquement a l'operation antidatee")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verantwortlichkeits-Code ist nur anwendbar auf einen zurückdatierten Handel.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de responsabilidad sólo se aplica a las operaciones antedatadas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code comptable ne s'applique qu'à une transaction antidatée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Rekenplichtigheidscode is alleen van toepassing op geantedateerde transacties")); }

        // Actions
	};
}



