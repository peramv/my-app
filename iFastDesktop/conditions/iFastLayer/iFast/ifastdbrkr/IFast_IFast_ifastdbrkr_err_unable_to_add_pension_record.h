#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_add_pension_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_add_pension_record() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_add_pension_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_PENSION_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add record, Pension Information already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht hinzugefügt werden, Renteninformation existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir un registro. La información de jubilación ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter l'enregistrement, l'information sur le fonds de pension existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd, pensioengegevens bestaan al")); }

        // Actions
	};
}



