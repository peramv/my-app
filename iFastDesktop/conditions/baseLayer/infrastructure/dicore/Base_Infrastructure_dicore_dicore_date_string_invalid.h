#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_date_string_invalid : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_date_string_invalid() { }
		~CBase_Infrastructure_dicore_dicore_date_string_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATE_STRING_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("compareHostGregorianDates recieved a Date string that does not match the HostMask format set in the Registry")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("compareHostGregorianDates recieved a Date string that does not match the HostMask format set in the Registry")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("compareHostGregorianDates erhielt eine Datenfolge, die nicht zum in der Registrierung festgelegten HostMask-Format passt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("compareHostGregorianDates recibió una cadena de fecha que no coincide con el formato de HostMask definido en el registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La comparaison des dates grégoriennes de l'hôte a reçu une chaîne de dates qui ne correspond pas au format du masque de l'hôte réglé dans le registre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("compareHostGregorianDates heeft een gegevensstring ontvangen die niet overeenkomt met de HostMask-indeling, zoals die is ingesteld in het register")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("check the date string format and make sure that HostMasks is defined in the registry under DICORE")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("check the date string format and make sure that HostMasks is defined in the registry under DICORE")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("überprüfen Sie das Datenstring-Format und vergewissern Sie sich, dass HostMasks in der Registrierung unter DICORE registriert ist.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el formato de la cadena de fecha y asegúrese de que HostMasks está definido en el registro bajo DICORE")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le format de la chaîne de dates et assurez-vous que les masques de l'hôte sont définis dans le registre avec DICORE.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de datumnotatie en zorg ervoor dat HostMasks is gedefinieerd in het register onder DICORE")); }
	};
}



