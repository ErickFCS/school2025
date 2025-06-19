import { z } from "zod";


export const jwtPayloadSchema = z.object({
    id: z.number().positive("The is must be positive")
});

export type JwtPayload = z.infer<typeof jwtPayloadSchema>
