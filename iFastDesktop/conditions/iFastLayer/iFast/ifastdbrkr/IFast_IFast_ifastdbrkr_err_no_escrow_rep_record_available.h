#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_escrow_rep_record_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_escrow_rep_record_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_escrow_rep_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ESCROW_REP_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Escrow Representative record available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Escrow Representative record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Escrow Rep-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro Escrow Rep disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de cessionnaire disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Escrow Rep record is niet beschikbaar")); }

        // Actions
	};
}



