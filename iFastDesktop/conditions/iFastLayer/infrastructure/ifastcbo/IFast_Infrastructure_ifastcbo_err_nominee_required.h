#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_nominee_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_nominee_required() { }
		~CIFast_Infrastructure_ifastcbo_err_nominee_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOMINEE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error redefining field. %oldName% length of %oldLength% is different from %newName% length of %newLength%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error redefining field. %oldName% length of %oldLength% is different from %newName% length of %newLength%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Redefinieren des Feldes. Die Länge %oldLength% des Feldes %oldName% ist anders als die Länge %newLength% des Feldes %newName%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al redefinir el campo. La longitud de %oldName% de %oldLength% es diferente de la longitud de %newName% de %newLength%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de redéfinition du champ. La longueur de %oldLength% du %oldName% est différente de la longueur de %newLength% du %newName%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij het opnieuw definiëren van veld. De lengte %oldLength% van %oldName% verschilt van de lengte %newLength% van %newName%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Eigenschaftendatei.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check properties file.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier des propriétés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bestand met eigenschappen")); }
	};
}



