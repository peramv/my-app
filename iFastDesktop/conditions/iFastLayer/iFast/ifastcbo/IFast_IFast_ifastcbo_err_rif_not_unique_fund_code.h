#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_not_unique_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_not_unique_fund_code() { }
		~CIFast_IFast_ifastcbo_err_rif_not_unique_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NOT_UNIQUE_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one record is allowed for Fund Code/Class Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Un seul enregistrement est autorisé pour CodeFonds/Codecatégorie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Fondscode/Klassencode ist nur ein Eintrag erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite un registro para el código de fondo/código de clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement est autorisé pour le code de fonds/classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één record toegestaan voor fondscode/categoriecode")); }

        // Actions
	};
}



