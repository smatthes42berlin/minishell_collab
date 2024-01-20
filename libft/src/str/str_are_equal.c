int	str_are_equal(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i])
		i++;
	if (s1[i] == s2[i])
		return (1);
	else
		return (0);
}
