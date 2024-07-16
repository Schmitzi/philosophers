#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philo
{
    int val;
    struct s_philo *next;
} t_philo;

t_philo *new_philo()
{
    t_philo *head = (t_philo *)malloc(sizeof(t_philo));
    if (head == NULL)
        return (NULL);
    head->val = 1;
    head->next = NULL;
    return (head);
}

t_philo *add_to_end(t_philo *philo)
{
    t_philo *new_node;
    t_philo *last;

    new_node = (t_philo *)malloc(sizeof(t_philo));
    if (new_node == NULL)
        return (NULL);
    new_node->val = philo->val + 1;
    new_node->next = NULL;
    if (philo == NULL)
        return new_node;
    last = philo;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return (philo);
}

int main(void)
{
    size_t i;
    t_philo *node;
    t_philo *temp;

    i = 0;
    node = new_philo();
    if (node == NULL)
        return (1);
    while (i++ < 2)
    {
        node = add_to_end(node);
        if (node == NULL)
            return (1);
    }
    temp = node;
    while (temp != NULL)
    {
        printf("%d\n", temp->val);
        temp = temp->next;
    }
    free(temp);
    return 0;
}
