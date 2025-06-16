import { z } from "zod";


export const dataSchema = z.object({
    espId: z.number(),
    timestamp: z.string().datetime(),
    type: z.string().min(1, "Type name is required"),
    value: z.string().min(1, "Value is required")
});

export type Data = z.infer<typeof dataSchema>
