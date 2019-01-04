#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_disessn_disessn_awd_not_logged_on : public CConditionObject
	{
	public:
		CIFast_IFast_disessn_disessn_awd_not_logged_on() { }
		~CIFast_IFast_disessn_disessn_awd_not_logged_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DISESSN_AWD_NOT_LOGGED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add a record, Account already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to add a record, Account already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht hinzugefügt werden, Konto existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir un registro. La cuenta ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un enregistrement, le compte existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd, het account bestaat al")); }

        // Actions
	};
}



