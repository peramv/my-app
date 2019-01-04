namespace ViewsGenerator
{
    using System.Collections.Generic;
    using System.Text.RegularExpressions;

    public static class StringExtension
    {
        public static string ReplaceFirst(this string text, string search, string replace)
        {
            int pos = text.IndexOf(search);

            if (pos < 0)
            {
                return text;
            }

            return text.Substring(0, pos) + replace + text.Substring(pos + search.Length);
        }

        public static string ReplaceCaseInsensitive(this string str, string from, string to)
        {
            str = Regex.Replace(str, from, to, RegexOptions.IgnoreCase);
            return str;
        }

        public static string RemoveTextAfterFirstChar(this string text, char c)
        {
            int firstIndexOfSeparator;

            if (!string.IsNullOrEmpty(text) &&
                ((firstIndexOfSeparator = text.IndexOf(c)) > -1))
            {
                return text.Remove(firstIndexOfSeparator);
            }
            else
            {
                return text;
            }
        }

        public static string RemoveTextAfterLastChar(this string text, char c)
        {
            int lastIndexOfSeparator;

            if (!string.IsNullOrEmpty(text) &&
                ((lastIndexOfSeparator = text.LastIndexOf(c)) > -1))
            {
                return text.Remove(lastIndexOfSeparator);
            }
            else
            {
                return text;
            }
        }

        /// <summary>
        /// Get string value between [first] a and [last] b.
        /// </summary>
        public static string Between(this string value, string a, string b)
        {
            int posA = value.IndexOf(a);
            int posB = value.LastIndexOf(b);

            if (posA == -1)
            {
                return string.Empty;
            }

            if (posB == -1)
            {
                return string.Empty;
            }

            int adjustedPosA = posA + a.Length;
            if (adjustedPosA >= posB)
            {
                return string.Empty;
            }

            return value.Substring(adjustedPosA, posB - adjustedPosA);
        }

        /// <summary>
        /// Get string value Before [first] a.
        /// </summary>
        public static string Before(this string value, string a)
        {
            int posA = value.IndexOf(a);
            if (posA == -1)
            {
                return string.Empty;
            }

            return value.Substring(0, posA);
        }

        /// <summary>
        /// Get string value after [last] a.
        /// </summary>
        public static string After(this string value, string a)
        {
            int posA = value.LastIndexOf(a);
            if (posA == -1)
            {
                return string.Empty;
            }
            
            int adjustedPosA = posA + a.Length;
            if (adjustedPosA >= value.Length)
            {
                return string.Empty;
            }

            return value.Substring(adjustedPosA);
        }
    }
}
