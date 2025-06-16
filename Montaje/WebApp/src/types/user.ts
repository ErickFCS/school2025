import { z } from "zod";


export const userSchema = z.object({
    password: z.string().min(6, "Password must be at least 6 characters").max(100, "Password must be less than 100 characters"),
    username: z.string().min(1, "Username is required").max(50, "Username must be less than 50 characters")
});

export type User = z.infer<typeof userSchema>;

export const userWithIdSchema = userSchema.extend({
    id: z.number().int().positive("ID must be a positive integer")
});

export type UserWithId = z.infer<typeof userWithIdSchema>;
