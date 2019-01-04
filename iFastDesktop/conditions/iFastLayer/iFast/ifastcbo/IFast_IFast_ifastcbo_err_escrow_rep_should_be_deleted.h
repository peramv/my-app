#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_rep_should_be_deleted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_rep_should_be_deleted() { }
		~CIFast_IFast_ifastcbo_err_escrow_rep_should_be_deleted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_REP_SHOULD_BE_DELETED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow representative should be deleted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow representative should be deleted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Repräsentant sollte gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe eliminarse el representante de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le cessionnaire devrait être supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pandvertegenwoordiger moet worden gewist")); }

        // Actions
	};
}



