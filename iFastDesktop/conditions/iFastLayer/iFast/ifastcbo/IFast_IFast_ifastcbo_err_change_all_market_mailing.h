#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_change_all_market_mailing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_change_all_market_mailing() { }
		~CIFast_IFast_ifastcbo_err_change_all_market_mailing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CHANGE_ALL_MARKET_MAILING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Change all other Marketing mailing flags on all other accounts for shareholder %SHRNBR% %SHRNAME%?")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Modifiez tous les autres indicateurs de mailing marketing dans tous les comptes de l'actionnaire %SHRNBR% %SHRNAME% ?")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Alle anderen Marketing-Mail-Kennzeichen in allen anderen Konten des Aktionärs %SHRNBR% %SHRNAME% ändern?")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("¿Cambiar todos los demás flags de correspondencia de marketing en todas las demás cuentas del accionista %SHRNBR% %SHRNAME%?")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changer tous les autres signaux de marketing par la poste de tous les autres comptes de l'actionnaire %SHRNAME% %SHRNBR%?")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alle overige vlaggen voor marketingmailings in alle overige accounts van aandeelhouder %SHRNBR% %SHRNAME% wijzigen?")); }

        // Actions
	};
}



