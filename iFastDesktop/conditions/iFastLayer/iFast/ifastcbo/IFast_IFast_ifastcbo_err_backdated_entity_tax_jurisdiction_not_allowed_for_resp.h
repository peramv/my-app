#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_backdated_entity_tax_jurisdiction_not_allowed_for_resp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_backdated_entity_tax_jurisdiction_not_allowed_for_resp() { }
		~CIFast_IFast_ifastcbo_err_backdated_entity_tax_jurisdiction_not_allowed_for_resp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BACKDATED_ENTITY_TAX_JURISDICTION_NOT_ALLOWED_FOR_RESP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date of the Entity’s Tax Jurisdiction must be after current business date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'effet de la juridiction fiscale de l'entité doit être ultérieure à la date du jour ouvrable courant.")); }

        // Actions
	};
}



