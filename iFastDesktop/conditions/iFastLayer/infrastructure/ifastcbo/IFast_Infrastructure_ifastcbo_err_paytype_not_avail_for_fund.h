#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_paytype_not_avail_for_fund : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_paytype_not_avail_for_fund() { }
		~CIFast_Infrastructure_ifastcbo_err_paytype_not_avail_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYTYPE_NOT_AVAIL_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Data object has no repeat records.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Data object has no repeat records.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Datenobjekt hat keine Wiederholungseinträge.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto de datos no tiene registros repetidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet de données n'a aucun enregistrement de répétition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevensobject heeft geen herhalingsrecords")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that repeat records exist before calling this method.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that repeat records exist before calling this method.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob Wiederholungseinträge vorhanden sind, bevor Sie diese Methode aufrufen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify that repeat records exist before calling this method.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que les enregistrements de répétition existent avant d'appeler cette méthode.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of er herhalingsrecords bestaan voordat u deze methode aanroept")); }
	};
}



