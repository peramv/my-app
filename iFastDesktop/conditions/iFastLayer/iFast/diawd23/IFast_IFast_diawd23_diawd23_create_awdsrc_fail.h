#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_create_awdsrc_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_create_awdsrc_fail() { }
		~CIFast_IFast_diawd23_diawd23_create_awdsrc_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_CREATE_AWDSRC_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one active Accountholder entity must be created for client account designation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une entite Titulaire de compte (01) active doit être creee pour pouvoir attribuer un compte client.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein aktives Kontoinhaber (01)-Objekt muss für die Kunden-Konto-Zuweisung erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe crearse al menos una entidad de titular de cuenta activa (01) para la designación de cuenta de cliente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins une entité titulaire de compte active doit être créée pour la désignation du compte client.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één actieve accounthouderseenheid (01) zijn gemaakt voor klantaccount")); }

        // Actions
	};
}



