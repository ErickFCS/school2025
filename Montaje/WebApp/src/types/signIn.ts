import { z } from "zod";


export const signInSchema = z.object({
    id: z.number().positive("Id must be positive"),
    password: z.string().min(1, "Password is required")
});

export type SignIn = z.infer<typeof signInSchema>;
