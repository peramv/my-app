#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_add_esop_rec : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_add_esop_rec() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_add_esop_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_ESOP_REC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add a record, ESoP contract already exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag darf nicht hinzugefügt werden, EsoP-Vertrag existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir un registro. El contrato ESoP ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un enregistrement, un contrat RADE existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd, de ESoP-overeenkomst bestaat al")); }

        // Actions
	};
}



