#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_add_record_shareholder_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_add_record_shareholder_exists() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_add_record_shareholder_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add record, Shareholder already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to add record, Shareholder already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht hinzugefügt werden, Aktionär existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir un registro. El accionista ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un enregistrement, l'actionnaire existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd, de aandeelhouder bestaat al")); }

        // Actions
	};
}



