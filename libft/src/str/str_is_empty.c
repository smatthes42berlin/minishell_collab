int	str_is_empty(const char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0')
		return (1);
	return (0);
}
