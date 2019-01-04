#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delete_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delete_entity() { }
		~CIFast_IFast_ifastcbo_err_delete_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Entity is joint with RESP Beneficiary, so it can not be deleted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The Entity is joint with RESP Beneficiary, so it can not be deleted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Objekt ist verbunden mit RESP-Begünstigtem und kann somit nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La entidad es conjunta con Beneficiario RESP, en consecuencia no puede eliminarse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité est conjointe au bénéficiaire REEE, elle ne peut donc pas être supprimée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De eenheid is gezamenlijk met RESP-begunstigde, en kan dus niet worden gewist")); }

        // Actions
	};
}



