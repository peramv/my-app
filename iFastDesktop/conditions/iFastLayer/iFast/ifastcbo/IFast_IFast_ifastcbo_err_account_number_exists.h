﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_number_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_number_exists() { }
		~CIFast_IFast_ifastcbo_err_account_number_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number already exists in the database.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le numero de compte existe deja dans la base de donnees")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer existiert bereits in der Datenbank.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta ya existe en la base de datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte existe déjà dans la base de données.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer bestaat al in de database")); }

        // Actions
	};
}



