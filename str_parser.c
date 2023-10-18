/**
 * parse_string - Parses the input string and writes tokens to a linked list
 * @str: Pointer to the token stream
 *
 * Return: NULL if failure, the head of the queue if successful
 */
queue_t *parse_string(char *str)
{
	char **raw_tokens, **sub_tokens;
	char separator = '\0';
	int beg_ind = 0, tok_ind = 0, end_ind = -1, sep_ind = -1;

	queue_t *q = NULL;

	if (!str)
		return (NULL);

	q = create_queue();
	if (!q)
		return (NULL);
	raw_tokens = strtow(str, NORM_DELIMS);

	if (!raw_tokens)
		return (NULL);

	while (raw_tokens[tok_ind])
	{
		if (is_logic(raw_tokens[tok_ind + 1]))
		{
			end_ind = tok_ind;
			sub_tokens = get_command_tokens(raw_tokens, beg_ind, end_ind);
			if (!sub_tokens)
				return (free_parser_tokens(raw_tokens, q));
			separator = get_separator(raw_tokens, sep_ind);
			if (!enqueue(q, separator, sub_tokens))
				return (free_sub_tokens_and_queue(sub_tokens, raw_tokens, q));
			sep_ind = tok_ind + 1;
			beg_ind = sep_ind + 1;
		}
		tok_ind++;
	}
	free_token_list(raw_tokens);
	return (q);
}

char get_separator(char **raw_tokens, int sep_ind)
{
	return (sep_ind >= 0 ? *raw_tokens[sep_ind] : '\0');
}

queue_t *free_parser_tokens(char **raw_tokens, queue_t *q)
{
	free_token_list(raw_tokens);
	free_command_queue(q);
	return (NULL);
}

queue_t *free_sub_tokens_and_queue(char **sub_tokens, char **raw_tokens,
		queue_t *q)
{
	free_token_list(sub_tokens);
	free_parser_tokens(raw_tokens, q);
	return (NULL);
}

