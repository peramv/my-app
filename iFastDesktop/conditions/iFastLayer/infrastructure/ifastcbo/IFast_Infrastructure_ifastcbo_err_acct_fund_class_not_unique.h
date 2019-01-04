#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acct_fund_class_not_unique : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acct_fund_class_not_unique() { }
		~CIFast_Infrastructure_ifastcbo_err_acct_fund_class_not_unique() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_FUND_CLASS_NOT_UNIQUE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From object and to object were registered with CBObase using different _registerSubclass() methods.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("From object and to object were registered with CBObase using different _registerSubclass() methods.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Von-Objekt und Zu-Objekt wurden mit CBObase unter Verwendung von anderen _registerSubclass()–Methoden registriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("From object and to object were registered with CBObase using different _registerSubclass() methods.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les objets source et cible ont été enregistrés avec un fondement CBO par l'utilisation de méthodes different _registerSubclass().")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("From object and to object were registered with CBObase using different _registerSubclass() methods")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Change both objects to use the new style _registerSubclass() method.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Change both objects to use the new style _registerSubclass() method.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Ändern Sie beide Objekte, um die neue Methode _registerSubclass() zu verwenden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Change both objects to use the new style _registerSubclass() method.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Changez les deux objets pour utiliser la nouvelle méthode style _registerSubclass().")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Wijzig beide objecten zodat de nieuwe methode style _registerSubclass() wordt gebruikt")); }
	};
}



